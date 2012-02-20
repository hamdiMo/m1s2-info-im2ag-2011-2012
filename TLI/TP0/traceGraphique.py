#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from math import *


def help():
	sys.stdout.write("********************************************************************************\n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  Trace.py : modified 01/01/2012                                                \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  [INTRODUCTION]                                                                \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("     Ce programme permet l'affichage d'un tableau de valeur d'une fonction de x \n")
	sys.stdout.write("  passé en argument via la ligne de commande.                                   \n")
	sys.stdout.write("  Les points de la fonction sont calculées dans l'intervalle [0..1] avec un     \n")
	sys.stdout.write("  ensemble de 10 valeurs.                                                       \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  [OPTIONS]                                                                     \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  --minimum, -m : permet de changer la valeur du debut de l'intervalle          \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  --maximum, -M : permet de changer la valeur de fin de l'intervalle            \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  --step, -s    : permet de modifier le nombre de valeurs a calculer dans       \n")
	sys.stdout.write("                  l'intervalle                                                  \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  --output, -o  : permet de rediriger la sortie vers un fichier                 \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("  --help, -h    : permet d'afficher l'aide                                      \n")
	sys.stdout.write("                                                                                \n")
	sys.stdout.write("********************************************************************************\n")


def traceRepere(xmin, xmax, ymin, ymax, output):
	output.write("/cmX { 1.0 mul } def %28.3464567 mul } def\n") # % (512/(xmax-xmin)))
	output.write("/cmY { 30.0 mul } def %28.3464567 mul } def\n")

	#output.write("[3] 0 setdash\n")
	output.write(".3 setgray\n")

	output.write("/Arial findfont 5 scalefont setfont\n")
	output.write("%s cmX %s cmY translate\n" % (-xmin, -ymin))
	output.write("10 10 translate\n")

	output.write(".2 setlinewidth\n")
	output.write("newpath\n")
	output.write("%s cmX 0 moveto\n" % (xmin))
	output.write("%s cmX 0 lineto (x) show\n" % (xmax))

	output.write("0 %s cmY moveto\n" % (ymin))
	output.write("0 %s cmY lineto (y) show\n" % (ymax))

	output.write("%s cmX %s cmY moveto\n" % (xmin, ymin))
	output.write("%s cmX %s cmY lineto\n" % (xmin, ymax))
	output.write("%s cmX %s cmY lineto\n" % (xmax, ymax))
	output.write("%s cmX %s cmY lineto\n" % (xmax, ymin))
	output.write("%s cmX %s cmY lineto\n" % (xmin, ymin))

	output.write("stroke\n")

	#output.write("[] 0 setdash\n")


def tracebis(function, xmin, xmax, nstep, output):
	output.write("%!\n")

	
	function = eval("lambda x:" + function)
	step = 1.*(xmax-xmin)/nstep

	ymin, ymax = function(xmin), function(xmin)
	for i in range(nstep+1):
		x = xmin + i*step
		try:
			y = function(x)
			if y < ymin:
				ymin = y
			elif y > ymax:
				ymax = y
		except:
			continue
	
	traceRepere(xmin, xmax, ymin, ymax, output)

	output.write("0 setgray\n")
	output.write(".4 setlinewidth\n")
        output.write("newpath\n")
	output.write("%s cmX %s cmY moveto\n" % (xmin, function(xmin)))

	for i in range(nstep+1):
		x = xmin + i*step
		try:
			y = function(x)
		except:
			continue
		output.write("%s cmX %s cmY lineto\n" % (x, y))

	output.write("stroke\n")

        output.write("showpage\n")
		
def trace(function, xmin, xmax, nstep, output):
    function = eval("lambda x:" + function)
    output.write('%!\n')

    # definition du repere
    output.write('/cm { 28.3464567 mul } def\n')
    output.write('/repere {\n')
    output.write('  /Arial findfont\n')
    output.write('  .5 cm scalefont\n')
    output.write('  setfont\n')
    output.write('  newpath\n')
    output.write('  0 0 moveto\n')
    output.write('  %g 0 lineto\n' % (xmax*20))
    output.write('  (x) show\n')
    output.write('  0 0 moveto\n')
    output.write('  %g 0 lineto\n' % (xmin*20))
    output.write('  0 0 moveto\n')
    output.write('  0 5 cm lineto\n')
    output.write('  (y) show\n')
    output.write('  0 0 moveto\n')
    output.write('  0 -5 cm lineto\n')
    output.write('  stroke\n')
    output.write('} def\n')
    output.write(' 10 cm 12 cm translate\n')
    output.write('repere\n')
    
    step = 1.*(xmax-xmin)/nstep
    
    # definition du quadrillage
    output.write('/quadrillage {\n')
    output.write('  newpath\n')
    output.write('  [5 5] 0 setdash \n')
    output.write('  0 0 moveto\n')
    for j in range((nstep)/10 + 1):
        x = xmin + j*step*10 
        output.write('  %g -5 cm moveto\n' % (x*20))
        output.write('  %g 5 cm lineto\n' % (x*20))
    output.write('  stroke\n')
    output.write('  [] 0 setdash\n')
    output.write('  0 0 moveto\n')
    output.write('} def\n')
    output.write('quadrillage\n')

    output.write('newpath\n')
    output.write('%g %g moveto\n' % (xmin*20,function(xmin)*40))

    # calcul de la fonction et affichage de la ligne
    for i in range(nstep+1):
        x = xmin + i*step
        try:
            y = function(x)
        except:
            continue
        output.write('%g %g lineto\n' % (x*20,40*y))
    output.write('stroke\n')

    output.write('showpage\n')
    output.close


def main(argv=None):
	if argv is None:
		argv = sys.argv

	import getopt
	try:
		options, argv = getopt.gnu_getopt(argv[1:], "m:M:s:o:h", ["minimum=", "maximum=", "step=", "output=", "help"])
	except getopt.GetoptError, message:
		sys.stderr.write("%s\n" % message)
		sys.exit(1)

	if len(argv) != 1:
		help()
		sys.exit(1)

	function = argv[0]
	output = sys.stdout
	xmin, xmax = -5., 5.
	nstep = (int)(xmax-xmin) * 10

	for option, value in options:
		if option in ["-h", "--help"]:
			help()
			sys.exit(0)
		elif option in ["-o", "--output"]:
			output = file(value, "w")
		elif option in ["-m", "--minimum"]:
			xmin = float(value)
		elif option in ["-M", "--maximmum"]:
			xmax = float(value)
		elif option in ["-s", "--step"]:
			nstep = int(value)
		else:
			assert False, "unhandled option"

	trace(function, xmin, xmax, nstep, output)

if __name__ == "__main__":
	sys.exit(main())

