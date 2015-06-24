# -*- coding: utf-8 -*-

import numpy as np
import scipy as sp
import sympy as sym
import matplotlib as mpl    
import matplotlib.pyplot as plt
from pylab import *

import uncertainties as uc
import StringIO

from scipy.optimize import curve_fit,leastsq, minimize, fsolve
from scipy import signal
from scipy.special import erf
from uncertainties import ufloat,unumpy
from uncertainties.unumpy import exp, log, sqrt


h, minute, x, y, temp, dummi1, dummi2 = np.loadtxt("DatenKoordianten.csv", unpack=True)
















heatmap, xedges, yedges = np.histogram2d(y, x, bins=10)
extent = [xedges[0], xedges[-1], yedges[0], yedges[-1]]

plt.clf()
plt.imshow(heatmap, extent=extent)
plt.show()