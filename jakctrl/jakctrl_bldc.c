#include "jakctrl.h"
//
static sint u0duty_fr_f0x(float f0pk, float f0x1, float f0uzf)
{
	return (sint) f0_abs(_1Mf * f0pk * f0x1 / f0uzf);
}
static sint u0omeg_fr_f0omeg(float f0omeg, float f0pwmfreq)
{
	// omeg = 2πf 2π is 2^20 so
	return (sint) (f0omeg * _1Mf / _2pai / f0pwmfreq);
}
static float f0x_fr_u0x1(float f0pk, sint u0x1)
{
	return (float) u0x1 * 1.0e-6f * f0pk;
}
static float f0hzpk_fr_f0uzemf(float kve, float uzemf)
{
	return kve * uzemf / 60.0f;
}
static void stop(struct jakctrl_bldc *bldc)
{
	if (bldc->d0star > 1000) bldc->d0star = -4000;
}
static void estop(struct jakctrl_bldc *bldc)
{
	bldc->d0star = 0;
	PWMONOFF(off);
}
//
#define	factuzf	(0.01f)
#define	factizf	(00.1f)
//
static VOID work_feed(struct jakctrl_bldc *bldc)
{
	bldc->feed->d0izavr = aver_of_cir64(&bldc->cir64izorg);
	bldc->feed->d0uzavr = aver_of_cir64(&bldc->cir64uzorg);
	bldc->feed->d0tmavr = aver_of_cir64(&bldc->cir64tmorg);
	//
	bldc->feed->f0uz = 1.0e-3f * (float) a0_ip1(0, bldc->para->m0uz4096, bldc->feed->d0uzavr);
	bldc->feed->f0iz = 1.0e-3f * (float) a0_ip1(bldc->para->m0iz0, bldc->para->m0iz4096, bldc->feed->d0izavr);
	//
	bldc->feed->f0uz = f0_sat(bldc->feed->f0uz, 1.0e+6f, bldc->para->f0uzpk * 0.2f);
	bldc->f0uzf = f0_iir(bldc->f0uzf, bldc->feed->f0uz, factuzf); //100ms
	bldc->f0izf = f0_iir(bldc->f0izf, f0_abs(bldc->feed->f0iz), factizf);	//10ms
}
static VOID work_para(struct jakctrl_bldc *bldc)
{
	bldc->f0xs = bldc->hz.f0omega * bldc->para->f0ls;
	bldc->f0zs = f0_root2(sqr(bldc->para->f0rs) + sqr(bldc->f0xs));
	bldc->f0ite = 1.6f * bldc->para->f0wtpk / bldc->para->f0uzpk;
}
static VOID work_pk(struct jakctrl_bldc *bldc)
{
	bldc->pk.f0uzemf = bldc->f0uzf * 0.6f;	//0.667f;
	//
	bldc->pk.f0hz = f0hzpk_fr_f0uzemf(bldc->para->f0kve, bldc->pk.f0uzemf);
	bldc->pk.f0omega = _2pai * bldc->pk.f0hz;
	//
	bldc->pk.f0uoacc = bldc->f0zs * bldc->f0ite;
	//
	bldc->pk.f0uoidl = bldc->pk.f0uoacc * 0.25f;
	//
	bldc->pk.f0uoizf = bldc->f0izf * bldc->f0zs * 0.8f; //frwd
}
static VOID work_hz(struct jakctrl_bldc *bldc)
{
	bldc->hz.f0omega = bldc->s0ref.f0rtf1 * bldc->pk.f0omega;
	bldc->hz.f0uoemf = bldc->s0ref.f0rtf1 * bldc->pk.f0uzemf;
	bldc->hz.u0omega1 = u0omeg_fr_f0omeg(bldc->hz.f0omega, 16.384e+3f); //32kpwm
	bldc->hz.u0uoemf1 = u0duty_fr_f0x(bldc->pk.f0uzemf, bldc->s0ref.f0rtf1, bldc->f0uzf);
	bldc->hz.u0uoidl1 = u0duty_fr_f0x(bldc->pk.f0uoidl, bldc->s0ref.f0rtf1, bldc->f0uzf);
}
static VOID work_ac(struct jakctrl_bldc *bldc)
{
	bldc->te.u0uoacc1 = u0duty_fr_f0x(bldc->pk.f0uoacc, bldc->s0ref.f0acf1, bldc->f0uzf);
	bldc->te.u0dummy1 = u0duty_fr_f0x(bldc->pk.f0uoizf, 1.0f, bldc->f0uzf);
	bldc->te.u0uoizf1 = d0_sat0(bldc->te.u0dummy1 - bldc->te.u0uoacc1 - bldc->hz.u0uoidl1, u0one);
}
static VOID work_ff(struct jakctrl_bldc *bldc)
{
	bldc->ff.u0uoext1 = bldc->hz.u0uoidl1 + bldc->te.u0uoacc1 + bldc->te.u0uoizf1;
	bldc->ff.u0uoexe1 = d0_sat0(bldc->ff.u0uoext1 + bldc->hz.u0uoemf1, u0one);
	//
	bldc->ff.shift = 5 + 7; //5 32k 7 127
}
static VOID work_view(struct jakctrl_bldc *bldc)
{
	bldc->view.f0hzrt = bldc->pk.f0hz * bldc->s0ref.f0rtf1;
	bldc->view.f0uoexe = f0x_fr_u0x1(bldc->f0uzf, bldc->ff.u0uoexe1);
	bldc->view.f0uoext = f0x_fr_u0x1(bldc->f0uzf, bldc->ff.u0uoext1);
	bldc->view.f0uoacc = f0x_fr_u0x1(bldc->f0uzf, bldc->te.u0uoacc1);
	bldc->view.f0uoidl = f0x_fr_u0x1(bldc->f0uzf, bldc->hz.u0uoidl1);
	bldc->view.f0uoizf = f0x_fr_u0x1(bldc->f0uzf, bldc->te.u0uoizf1);
}
static VOID work_star(struct jakctrl_bldc *bldc)
{
	bldc->f0idz = 0.9 * bldc->view.f0uoexe / bldc->f0zs;
	bldc->f0idzf = f0_iir(bldc->f0idzf, bldc->f0idz, factizf);
	if (bldc->f0izf > bldc->f0idzf && bldc->hz.u0uoemf1 > u0one / 4)
	{
		stop(bldc);
	}
	//
	if (bldc->feed->f0uz > bldc->para->f0uzpk) estop(bldc);
	//
	if (bldc->d0star++ < 0) //normal close
	{
		bldc->d0starfact = 0;
	}
	else //
	if (bldc->d0star == 0)
	{
		bldc->d0starfact = 0;
		PWMONOFF(off);
	}
	else //
	if (bldc->d0star == 1000)
	{
		bldc->d0starfact = 0;
		PWMONOFF(onn);
	}
	else //
	if (bldc->d0star == 3000)
	{
		bldc->d0starfact = 16;
	}
	else //
	if (bldc->d0star > 3000)
	{
		bldc->d0star = 3197;
	}
	else ;
}
void work_jakctrl_bldc(struct jakctrl_bldc *bldc, struct jakctrl_bldc_para *para, struct jakctrl_bldc_feed *feed)
{
	if (bldc->para == 0) bldc->para = para;
	if (bldc->feed == 0) bldc->feed = feed;
	//
	work_feed(bldc);
	//
	work_para(bldc);
	//
	work1ms_jakctrl_ref(&bldc->s0ref, (bldc->feed->m0hz1 * bldc->d0starfact), 12);
	//
	work_star(bldc);
	//
	work_pk(bldc);
	//
	work_hz(bldc);
	//
	work_ac(bldc);
	//
	work_ff(bldc);
	//
	work_view(bldc);
}
//
static const word cw257pwm[257] =
{
	0, 696, 1392, 2087, 2781, 3473, 4163, 4851, 5535, 6216, 6894, 7567, 8236, 8900, 9558, 10211, 10858, 11498, 12131, 12757,
	13375, 13985, 14318, 14509, 14691, 14864, 15029, 15184, 15330, 15467, 15595, 15713, 15822, 15921, 16011, 16091, 16162,
	16222, 16273, 16314, 16345, 16367, 16378, 16380, 16372, 16354, 16326, 16288, 16240, 16183, 16116, 16039, 15953, 15857,
	15751, 15636, 15511, 15378, 15234, 15082, 14921, 14750, 14571, 14383, 14186, 14383, 14571, 14750, 14921, 15082, 15234,
	15378, 15511, 15636, 15751, 15857, 15953, 16039, 16116, 16183, 16240, 16288, 16326, 16354, 16372, 16380, 16378, 16367,
	16345, 16314, 16273, 16222, 16162, 16091, 16011, 15921, 15822, 15713, 15595, 15467, 15330, 15184, 15029, 14864, 14691,
	14509, 14318, 13985, 13375, 12757, 12131, 11498, 10858, 10211, 9558, 8900, 8236, 7567, 6894, 6216, 5535, 4851, 4163, 3473,
	2781, 2087, 1392, 696, 0, -696, -1392, -2087, -2781, -3473, -4163, -4851, -5535, -6216, -6894, -7567, -8236, -8900, -9558,
	-10211, -10858, -11498, -12131, -12757, -13375, -13985, -14318, -14509, -14691, -14864, -15029, -15184, -15330, -15467,
	-15595, -15713, -15822, -15921, -16011, -16091, -16162, -16222, -16273, -16314, -16345, -16367, -16378, -16380, -16372,
	-16354, -16326, -16288, -16240, -16183, -16116, -16039, -15953, -15857, -15751, -15636, -15511, -15378, -15234, -15082,
	-14921, -14750, -14571, -14383, -14186, -14383, -14571, -14750, -14921, -15082, -15234, -15378, -15511, -15636, -15751,
	-15857, -15953, -16039, -16116, -16183, -16240, -16288, -16326, -16354, -16372, -16380, -16378, -16367, -16345, -16314,
	-16273, -16222, -16162, -16091, -16011, -15921, -15822, -15713, -15595, -15467, -15330, -15184, -15029, -14864, -14691,
	-14509, -14318, -13985, -13375, -12757, -12131, -11498, -10858, -10211, -9558, -8900, -8236, -7567, -6894, -6216, -5535,
	-4851, -4163, -3473, -2781, -2087, -1392, -696, 0,
//
};
VOID calc_jakctrl_bldc_pwm(struct jakctrl_bldc *bldc, sint u0omeg, sint d0arrhalf, sint u0norm)
{
	bldc->pwm.W0cmprHalf = u0_mpy(u0norm, d0arrhalf);
	bldc->pwm.u0cita = (u0omeg + bldc->pwm.u0cita) & u0max;
	bldc->pwm.d0tmp1 = a0_lookword(cw257pwm, (bldc->pwm.u0cita), 257);
	bldc->pwm.d0tmp2 = a0_lookword(cw257pwm, (bldc->pwm.u0cita + (u0one / 3)) & u0max, 257);
	bldc->pwm.d0tmp3 = a0_lookword(cw257pwm, (bldc->pwm.u0cita - (u0one / 3)) & u0max, 257);
	bldc->pwm.W0cmprA = d0arrhalf + g0_mpy(bldc->pwm.d0tmp1, bldc->pwm.W0cmprHalf);
	bldc->pwm.W0cmprB = d0arrhalf + g0_mpy(bldc->pwm.d0tmp2, bldc->pwm.W0cmprHalf);
	bldc->pwm.W0cmprC = d0arrhalf + g0_mpy(bldc->pwm.d0tmp3, bldc->pwm.W0cmprHalf);
}
VOID itrr_jakctrl_bldc(struct jakctrl_bldc *bldc, sint d0arr, sint d0izorg, sint d0uzorg, sint d0tmorg)
{
	if (bldc->para == 0) return;
	if (bldc->feed == 0) return;
	//
	if (d0izorg > 3800) estop(bldc);
	//
	push_to_cir64(&bldc->cir64izorg, 20, d0izorg);
	push_to_cir64(&bldc->cir64uzorg, 20, d0uzorg);
	push_to_cir64(&bldc->cir64tmorg, 20, d0tmorg);
	//
	bldc->fast.u0omeg = d0_slop(bldc->hz.u0omega1, bldc->fast.u0omeg, u0one >> bldc->ff.shift);
	bldc->fast.u0uexe = d0_slop(bldc->ff.u0uoexe1, bldc->fast.u0uexe, u0one >> bldc->ff.shift);
	//
	calc_jakctrl_bldc_pwm(bldc, bldc->fast.u0omeg, d0arr >> 1, bldc->fast.u0uexe);
}
//
