# -*- coding: utf-8 -*-

import numpy as np
import scipy as sp
import sympy as sym
import matplotlib as mpl    
import matplotlib.pyplot as plt
from pylab import *

import uncertainties as uc
from scipy.optimize import curve_fit
from uncertainties import ufloat,unumpy

def linReg(xdata,ydata,yerr=None): 
    """
    Führt eine lineare Regression durch, wobei Fehler im y-Wert 
    berücksichtigt werden können. Falls yerr=None, so wird als Fehler die 
    Streuung der Werte um die Gerade genommen (Regression ohne bekannte Fehler).
    """
    if yerr is None: w = 1.0*np.ones_like(xdata)
    elif isinstance(yerr, np.generic): w = ( 1/(float(yerr)**2) )*np.ones_like(xdata)
    else: w = 1/yerr**2
    
    wsum = np.sum(w)
    xsum = np.sum(xdata*w)
    xsqsum = np.sum((xdata**2)*w)
    ysum = np.sum(ydata*w)
    xysum = np.sum(xdata*ydata*w)    
    
    delta = wsum*xsqsum - xsum**2
    
    m = (wsum*xysum - xsum*ysum)/delta
    b = (xsqsum*ysum - xsum*xysum)/delta
 
    merr = np.sqrt(wsum/delta)
    berr = np.sqrt(xsqsum/delta)  

    if yerr is None:
        stddev = np.sqrt( np.sum((ydata - m*xdata - b)**2)/(len(xdata)-2) )
        
        merr = merr*stddev
        berr = berr*stddev  
        
    return np.array([m,b]), np.array([merr,berr])
    
    
def stddev(xdata,ydata):
    """
    Es wird eine lineare Regression der Daten ausgeführt. Dannach wird dich
    Streuung der y-Werte um diese Gerade zurückgegeben (Standardabweichung)
    """
    w = np.ones_like(xdata)
    wsum = np.sum(w)
    xsum = np.sum(xdata*w)
    xsqsum = np.sum((xdata**2)*w)
    ysum = np.sum(ydata*w)
    xysum = np.sum(xdata*ydata*w)    
    
    delta = wsum*xsqsum - xsum**2
    
    m = (wsum*xysum - xsum*ysum)/delta
    b = (xsqsum*ysum - xsum*xysum)/delta

    stddev = np.sqrt( np.sum((ydata - m*xdata - b)**2)/(len(xdata)-2) )
    return stddev
        
    
def linReg_iter(xdata, ydata, yerr, xerr, mtol=1.49012e-8):
    """
    Führt über linReg iterativ eine lineare Regression durch, damit auch Fehler
    in den x-Werten berücksichtigt werden können.
    """
    if yerr is None: yerr_tmp = stddev(xdata,ydata)
    else: yerr_tmp = yerr
    
    popt, perr = linReg(xdata,ydata,yerr)
    m = popt[0]
    #print m
    err = np.sqrt(yerr_tmp**2 + (m*xerr)**2)
    popt, perr = linReg(xdata,ydata,err)
    while np.abs(m-popt[0]) > mtol:
        m = popt[0]
        #print m
        err = np.sqrt(yerr_tmp**2 + (m*xerr)**2)
        popt, perr = linReg(xdata,ydata,err)
    return popt,perr
    
    
def ulinReg(xdata,ydata):
    """
    Führt über linReg_iter eine lineare Regression durch. Parameter sind hierbei
    allerdings uncertainties.ufloat
    """
    popt, perr = linReg_iter(unumpy.nominal_values(xdata),
                 unumpy.nominal_values(ydata), unumpy.std_devs(ydata),
                 unumpy.std_devs(xdata))
    return uc.ufloat(popt[0],perr[0]), uc.ufloat(popt[1],perr[1])
    
    
    
def weightedAverage(data, err):
    """
    Berechnet den gewichteten Mittelwert mit Fehler
    """
    if err is None: w = 1.0*np.ones_like(data)
    elif isinstance(err, np.generic): w = ( 1/(float(err)**2) )*np.ones_like(xdata)
    else: w = 1/err**2
    
    mean = np.sum(w*data)/np.sum(w)
    sigma = np.sqrt(1/np.sum(w))    
    
    if err is None:
        sigma = np.std(ddof=1)*sigma
        
    return mean, sigma
    
    
def uweightedAverage(data):
    mean, sigma = weightedAverage(unumpy.nominal_values(data), unumpy.std_devs(data))
    return ufloat(mean, sigma)
    
    
def propReg(xdata,ydata):
    m = np.sum(xdata*ydata)/np.sum(xdata*xdata)
    stddev = np.sqrt( np.sum((ydata - m*xdata)**2)/(len(xdata)-1) )
    uydata = unumpy.uarray(ydata,stddev)
    #uxdata = unumpy.uarray(xdata,stddev)
    return np.sum(xdata*uydata)/np.sum(xdata*xdata)
    
def propReg2(xdata,ydata):
    m = np.sum(xdata*ydata)/np.sum(xdata*xdata)
    stddev = np.sqrt( np.sum((ydata - m*xdata)**2)/(len(xdata)-1) )
    uydata = unumpy.uarray(ydata,stddev)
    #uxdata = unumpy.uarray(xdata,stddev)
    um = np.sum(xdata*uydata)/np.sum(xdata*xdata)
    return np.array([uc.nominal_value(um), 0]), np.array([uc.std_dev(um), 0])    
    
def upropReg(xdata,ydata):
    return np.sum(xdata*ydata)/np.sum(xdata*xdata)
    
def propStddev(xdata,ydata):
    m = np.sum(xdata*ydata)/np.sum(xdata*xdata)
    stddev = np.sqrt( np.sum((ydata - m*xdata)**2)/(len(xdata)-1) )
    return stddev
    
def myplot(xdata,ydata, c='r', label=None):
    x  = uc.unumpy.nominal_values(xdata)
    y  = uc.unumpy.nominal_values(ydata)
    return plt.plot(x, y, c, lw=2, label=label)
    
def uplot(xdata, ydata, c='k', marker='s', ms=4, mew=1, lw=1, label=None):
    x  = uc.unumpy.nominal_values(xdata)
    y  = uc.unumpy.nominal_values(ydata)
    xerr = uc.unumpy.std_devs(xdata)
    yerr = uc.unumpy.std_devs(ydata)
    return plt.errorbar(x,y, yerr, xerr, fmt=' ', ms=ms, mew=mew, lw=lw, \
                           mfc=c, mec=c, ecolor=c, marker=marker, label=label)[0]
        

def mysavefig(name, save=True):
    if save:
        plt.savefig(name+".pdf")
        plt.savefig(name+".svg")

#def plottext(x,y):
#    plt.text(0.53,0.04,u"$Q = \\kappa\\cdot x$\n"\
#                     u"$\\kappa = ( %.5f \pm %.5f )\,\\mathrm{\mu C}/\\mathrm{Skt}$"\
#                     % (kappa*1e9,perr1_3g[0]*1e6, popt1_3g[1]*1e3,perr1_3g[1]*1e3), fontsize = 16, 
#                     bbox=dict(fc='white',ec=None, pad=8), transform=ax.transAxes, 
#                    verticalalignment='bottom', horizontalalignment='left', linespacing=0.9)