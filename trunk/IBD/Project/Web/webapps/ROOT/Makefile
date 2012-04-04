.PHONY = init, build, start, shutdown, restart, test

CC=javac
#ssh -L 1521:localhost:1521 uyary@hopper.e.ujf-grenoble.fr
# Repertoire Hugo
CATALINA=~/Documents/Cours/M1/S2/IBD/Project/Web
#CATALINA=~/Documents/Cours/UJF/M1/S2/IBD/Project/Web

# Repertoire Yasin
CATALINA=~/M1/S2/SVNCOURS/IBD/Project/Web
#CATALINA=~/SVNCoursM1/IBD/Project/Web

init:
	export JAVA_HOME=/usr
#	export JAVA_HOME=/usr/lib/jvm/java-1.6.0-openjdk/
	export CATALINA_HOME=$(CATALINA)

build:
	$(CC) -d WEB-INF/classes -classpath .:classes:../../lib/servlet-api.jar:../../lib/ojdbc14.jar -sourcepath src/ src/*.java

start:
	$(CATALINA)/bin/startup.sh

shutdown:
	$(CATALINA)/bin/shutdown.sh

restart: shutdown start

test:
	java -classpath .:WEB-INF/classes:../../lib/ojdbc14.jar Test
