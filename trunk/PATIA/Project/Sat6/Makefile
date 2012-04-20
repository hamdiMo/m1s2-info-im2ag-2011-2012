.PHONY: test, trace




test:
	java SatTest 5 100 5 1000 statistics/data.plot

trace:
	cd statistics; gnuplot plotInstances
	cd statistics; gnuplot plotConflicts
	cd statistics; gnuplot plotMaxHeight
	cd statistics; gnuplot plotLearntClauses
	cd statistics; gnuplot plotSats
