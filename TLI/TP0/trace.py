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


def trace(function, xmin, xmax, nstep, output):
	output.write("x, %s\n" % function)
	function = eval("lambda x:" + function)

	step = 1.*(xmax-xmin)/nstep
	for i in range(nstep+1):
		x = xmin + i*step
		try:
			y = function(x)
		except:
			continue
		output.write("%s, %s\n" % (x, y))
		

def main(argv=None):
	if argv is None:
		argv = sys.argv

	import getopt
	try:
		options, argv = getopt.gnu_getopt(argv[1:], "m:M:o:h", ["minimum=", "maximum=", "output=", "help"])
	except getopt.GetoptError, message:
		sys.stderr.write("%s\n" % message)
		sys.exit(1)

	if len(argv) != 1:
		help()
		sys.exit(1)

	function = argv[0]
	output = sys.stdout
	xmin, xmax = 0., 1.
	nstep = 10

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
		else:
			assert False, "unhandled option"

	trace(function, xmin, xmax, nstep, output)

if __name__ == "__main__":
	sys.exit(main())







# output.write("%!")
# output.write("/cm { 28.3464567 mul } def\n")
# output.write("/repere { /Arial findfont .5 cm scalefont setfont newpath 0 0 moveto 1 cm 0 lineto (x) show 0 0 moveto 0 1 cm lineto (y) show stroke } def\n")
# output.write("repere\n")
# output.write("2 10 { == } for\n")
# output.write("showpage")	

