#include <math.h>

typedef struct {
	float v_alpha;
	float v_beta;
	float i_alpha;
	float i_beta;
	float flux_angle;
} foc_observer_ortega_input_t;

/*@
	ensures \result == \sqrt(x);
*/
float sqrtf(float x);

/*@
	ensures \result == \cos(x);
*/
float cosf(float x);

/*@
	ensures \result == \sin(x);
*/
float sinf(float x);

/*@
	ensures \result == \atan2(y, x);
*/
static float fast_atan2(float y, float x) {
	const float abs_y = fabsf(y) + 0.1f; // 1e-20;
	float angle;
	if (x >= 0.0f) {
		const float ratio = (x - abs_y) / (x + abs_y);
		const float ratio_squared = ratio * ratio;
		angle = ((0.1963 * ratio_squared) - 0.9817) * ratio
				+ (3.14159265358979323846 / 4.0);
	} else {
		const float ratio = (x + abs_y) / (abs_y - x);
		const float ratio_squared = ratio * ratio;
		angle = ((0.1963 * ratio_squared) - 0.9817) * ratio
				+ (3.0 * 3.14159265358979323846 / 4.0);
	}
	if (angle != angle) {
		angle = 0.0f;
	}
	//@ admit(\atan2(y, x) == (y < 0.0f ? -angle : angle));
	return y < 0.0f ? -angle : angle;
}


/* BASED ON:
  Sensorless Control of Surface-Mount Permanent-Magnet Synchronous Motors Based on a Nonlinear Observer, IEEE Transactions on Power Electronics, 25(2), 2010.
*/

/*@
	logic real Ld_Lq_diff = 0.00001f;
	logic real L_orig = 0.0001f; // stator inductance
	logic real R_s = 0.05f; // stator resistance
	logic real psi_m = 0.01f; // permanent magnetic flux linkage
	logic real dt = 0.00005f; // 
	logic real gamma = 6.0f;
	logic real L_fix(real id, real iq) =
		\abs(id) > 0.1 || \abs(iq) > 0.1 ? 
			L_orig - Ld_Lq_diff / 2.0 + Ld_Lq_diff * (iq * iq) / ((id * id) + (iq * iq)) : L_orig;

	logic real id_park(real angle, real i_alpha, real i_beta) = 
		\cos(angle) * i_alpha + \sin(angle) * i_beta;
	logic real iq_park(real angle, real i_alpha, real i_beta) = 
		\cos(angle) * i_beta  - \sin(angle) * i_alpha;
  logic real x1_fun(real i_alpha, real theta, real L) =  L * i_alpha + psi_m * \cos(theta);  //eq (3a)
	logic real x2_fun(real i_beta, real theta, real L) =  L * i_beta  + psi_m * \sin(theta);  //eq (3b)
	logic real yi(real i, real v) = (-R_s) * i + v;																					 //eq (4)
	logic real etai(real xi, real i, real L) = xi - L * i; 																							//eq (6)
	logic real err_fun(real x1, real x2, real i_alpha, real i_beta, real L) = 
		psi_m * psi_m
			- (etai(x1, i_alpha, L) * etai(x1, i_alpha, L)
				+ etai(x2, i_beta, L) * etai(x2, i_beta, L));
	logic real xi_dot(real xi, real i, real v, real err, real L) =
		yi(i, v)
			+ (gamma/2) * etai(xi, i, L)
				* (err > 0.0 ? 0.0 : err);
	logic real new_xi(real xi, real xi_dot) = xi + xi_dot * dt;
	logic real new_theta(real x1, real x2, real i_alpha, real i_beta, real L) = 
		\atan2(x2 - L * i_beta, x1 - L * i_alpha);
*/


/*
 * Standalone one-step VESC Ortega observer example.
 * Includes the Ortega mode update and all common observer post-processing.
 */

/*@
	requires \separated(id, iq);
	assigns *id, *iq;
	ensures *id == id_park(angle, i_alpha, i_beta);
	ensures *iq == iq_park(angle, i_alpha, i_beta);
*/
void park_transform(float angle, float i_alpha, float i_beta, float *id, float *iq){
		// Park transform
		*id = cosf(angle) * i_alpha + sinf(angle) * i_beta;
		*iq = cosf(angle) * i_beta  - sinf(angle) * i_alpha;
}

/*@
	requires \separated(x1, x2);
	assigns *x1, *x2;
	ensures *x1 == lambda * \cos(angle) + L_ia;
	ensures *x2 == lambda * \sin(angle) + L_ib;
*/
void estimate_prev_x(float lambda, float angle, float L_ia, float L_ib, float *x1, float *x2) {
	*x1 = lambda * cosf(angle) + L_ia;
	*x2 = lambda * sinf(angle) + L_ib;
}

/*
	ensures 
		\let id = id_park(flux_angle, i_alpha, i_beta);
		\let iq = iq_park(flux_angle, i_alpha, i_beta);
		\let L = L_fix(id, iq);
		\let x1 = x1_fun(i_alpha, flux_angle, L); 
		\let x2 = x2_fun(i_beta, flux_angle, L);
		\let err = err_fun(x1, x2, i_alpha, i_beta, L);
		\let x1_dot = xi_dot(x1, i_alpha, v_alpha, err, L);
		\let x2_dot = xi_dot(x2, i_beta,  v_beta,  err, L);
		\let new_x1 = new_xi(x1, x1_dot);
		\let new_x2 = new_xi(x2, x2_dot);
		\let flux_magnitude = \sqrt(new_x1 * new_x1 + new_x2 * new_x2);
		\let fix_new_x1 = flux_magnitude < (psi_m / 2) ? new_x1 * 1.1 : new_x1;
		\let fix_new_x2 = flux_magnitude < (psi_m / 2) ? new_x2 * 1.1 : new_x2;
		new_theta(fix_new_x1, fix_new_x2, i_alpha, i_beta, L) == \result;
*/
/*@
  \flostat::distribution v_alpha, "Uniform", -40.0, 40.0;
  \flostat::distribution v_beta, "Uniform", -40.0, 40.0;
  \flostat::distribution i_alpha, "Uniform", -100.0, 100.0;
  \flostat::distribution i_beta, "Uniform", -100.0, 100.0;
  \flostat::distribution flux_angle, "Uniform", -3.14159265, 3.14159265;
  \flostat::prob_ensures 0.99,
    \flteq(\result, 
				\let id = id_park(flux_angle, i_alpha, i_beta);
		\let iq = iq_park(flux_angle, i_alpha, i_beta);
		\let L = L_fix(id, iq);
		\let x1 = x1_fun(i_alpha, flux_angle, L); 
		\let x2 = x2_fun(i_beta, flux_angle, L);
		\let err = err_fun(x1, x2, i_alpha, i_beta, L);
		\let x1_dot = xi_dot(x1, i_alpha, v_alpha, err, L);
		\let x2_dot = xi_dot(x2, i_beta,  v_beta,  err, L);
		\let new_x1 = new_xi(x1, x1_dot);
		\let new_x2 = new_xi(x2, x2_dot);
		\let flux_magnitude = \sqrt(new_x1 * new_x1 + new_x2 * new_x2);
		\let fix_new_x1 = flux_magnitude < (psi_m / 2) ? new_x1 * 1.1 : new_x1;
		\let fix_new_x2 = flux_magnitude < (psi_m / 2) ? new_x2 * 1.1 : new_x2;
		new_theta(fix_new_x1, fix_new_x2, i_alpha, i_beta, L)
		, 2.96/8.0)
		;
*/
float main(
	float flux_angle, 
	float i_alpha,
	float i_beta,
	float v_alpha,
	float v_beta
) {
	const float resistance = 0.05f;
	float L = 0.0001f;
	const float Ld_Lq_diff = 0.00001f;
	const float lambda = 0.01f; //flux linkage
	const float gamma = 6.0f;
	const float dt = 0.00005f;
	
	
	//Get an estimate of the previous value of x.
	// For simplicity, we assume it is correct according to samples of input angle and currents.
	
	// Calculate id and iq according to Park transform:
	float id;
	float iq;
	park_transform(flux_angle, i_alpha, i_beta, &id, &iq);

	if (fabsf(id) > 0.1 || fabsf(iq) > 0.1) {
		L = L - Ld_Lq_diff / 2.0 + Ld_Lq_diff * (iq * iq) / ((id * id) + (iq * iq));
	}

	const float L_ia = L * i_alpha;
	const float L_ib = L * i_beta;
	const float R_ia = resistance * i_alpha;
	const float R_ib = resistance * i_beta;
	const float gamma_half = gamma * 0.5;
	float x1;
	float x2;
	estimate_prev_x(lambda, flux_angle, L_ia, L_ib, &x1, &x2);
	
	float err = lambda * lambda
			- ((x1 - L_ia) * (x1 - L_ia)
				+ (x2 - L_ib) * (x2 - L_ib));
	if (err > 0.0f) {
		err = 0.0f;
	}
	
	const float x1_dot = v_alpha - R_ia
			+ gamma_half * (x1 - L_ia) * err;
	const float x2_dot = v_beta - R_ib
			+ gamma_half * (x2 - L_ib) * err;
	x1 += x1_dot * dt;
	x2 += x2_dot * dt;
	
	if (x1 != x1) {
		x1 = 0.0f;
	}
	if (x2 != x2) {
		x2 = 0.0f;
	}
	
	const float flux_magnitude = sqrtf(x1 * x1 + x2 * x2);
	if (flux_magnitude < lambda * 0.5) {
		x1 *= 1.1;
		x2 *= 1.1;
	}
	const float y = x2 - L_ib;
	const float x = x1 - L_ia;
	
	return fast_atan2(y, x);
}
