.PHONY = rebuid

CATALINA = ~/Documents/Cours/M1/S2/IBD/TP2/apache-tomcat-6.0.14

rebuild:
	javac -d WEB-INF/classes -classpath .:classes:../../lib/servlet-api.jar src/*.java
	$(CATALINA)/bin/shutdown.sh
	$(CATALINA)/bin/startup.sh
