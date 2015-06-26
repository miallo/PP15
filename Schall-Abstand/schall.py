# -*- coding: utf-8 -*-
"""
Created on Thu Jun 25 22:54:56 2015

@author: jan
"""



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
from linReg import *




d, I1, I2, I3 = np.loadtxt("schall.dat", unpack=True)




wert   = np.ones_like(I3)
fehler = np.ones_like(I3)

for i in xrange(len(d)):
    wert[i]      = np.mean( np.array([I1[i], I2[i], I3[i] ]))
    fehler[i]    = np.std(  np.array([I1[i], I2[i], I3[i] ]),ddof=1)*1.3


















wert = uc.unumpy.uarray(wert/wert[-1], fehler/wert[-1])


d, derr, w, werr = uc.unumpy.nominal_values(d), uc.unumpy.std_devs(d), uc.unumpy.nominal_values(wert) , uc.unumpy.std_devs(wert) 

np.savetxt('mittel.csv',(d, derr, w, werr),delimiter=' ', newline='\n',)





#d = uc.unumpy.uarray(d,0.2)



plt.close('all')
mpl.rcParams['text.usetex']=True
mpl.rcParams['text.latex.unicode']=True
plt.rc('text', usetex=True)
plt.rc('font', family='serif')




plt.figure(1)
plt.grid(True)
plt.xlabel(u'Abstand $d$ [cm]', fontsize=14)
plt.ylabel(u'rel. Intensität $I/I0$', fontsize=14)
uplot(d, wert, label=u'Intensität')
#uplot(d, I1, label='test')
#uplot(d, I2, label='test')
#uplot(d, I3, label='test')
plt.legend(fontsize=16)