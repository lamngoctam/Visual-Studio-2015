// NUMERICAL RECIPES in C 
// http://www.library.cornell.edu/nr/bookcpdf/c11-1.pdf
#include <stdio.h>
#include <math.h>

#include <iostream>
using namespace std;

void Rotate(double a[4][4], double s, double tau, int i, int j, int k, int l)
{
	double h, g;
	g = a[i][j];
	h = a[k][l];
	a[i][j] = g - s * (h + g *tau);
	a[k][l] = h + s * (g - h *tau);
}

bool Jacobi(double(&a)[4][4], double(&v)[4][4], double(&d)[4])
{
	int n = 4;
	int i, j, iq, ip;
	double tresh, theta, tau, t, sm, s, h, g, c, b[4], z[4];

	for (ip = 0; ip < n; ip++){
		for (iq = 0; iq < n; iq++) v[ip][iq] = 0.0f;
		v[ip][ip] = 1.0f;
	}
	for (ip = 0; ip < n; ip++){
		b[ip] = d[ip] = a[ip][ip];
		z[ip] = 0.0f;
	}
	for (i = 0; i < 50; i++){
		sm = 0.0f;
		for (ip = 0; ip < n - 1; ip++){
			for (iq = ip + 1; iq < n; iq++) sm += (double)fabs(a[ip][iq]);
		}

		if (sm == 0.0f) return true;
		if (i < 4) tresh = 0.2f * sm / (n * n);
		else tresh = 0.0f;
		for (ip = 0; ip < n - 1; ip++){
			for (iq = ip + 1; iq < n; iq++){
				g = 100.0f * (double)fabs(a[ip][iq]);
				if (i > 4 && (fabs(d[ip]) + g) == fabs(d[ip])
					&& (fabs(d[iq]) + g) == fabs(d[iq])) a[ip][iq] = 0.0f;
				else if (fabs(a[ip][iq]) > tresh){
					h = d[iq] - d[ip];
					if ((fabs(h) + g) == fabs(h)) t = a[ip][iq] / h;
					else{
						theta = 0.5f * h / a[ip][iq];
						t = 1.0f / ((double)fabs(theta) + (double)sqrt(1.0f + theta * theta));
						if (theta < 0.0f) t = -t;
					}
					c = 1.0f / (double)sqrt(1 + t * t);
					s = t * c;
					tau = s / (1.0f + c);
					h = t * a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq] = 0.0f;

					for (j = 0; j < ip; j++) Rotate(a, s, tau, j, ip, j, iq);
					for (j = ip + 1; j < iq; j++) Rotate(a, s, tau, ip, j, j, iq);
					for (j = iq + 1; j < n; j++) Rotate(a, s, tau, ip, j, iq, j);
					for (j = 0; j < n; j++) Rotate(v, s, tau, j, ip, j, iq);
				}
			}
		}
		for (ip = 0; ip < n; ip++){
			b[ip] += z[ip];
			d[ip] = b[ip];
			z[ip] = 0.0f;
		}
	}
	return false;
}

