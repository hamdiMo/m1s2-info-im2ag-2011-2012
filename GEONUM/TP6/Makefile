


%.out: %.in
	java Surface $< > $@
	gnuplot < echo "splot '$@' w l"
