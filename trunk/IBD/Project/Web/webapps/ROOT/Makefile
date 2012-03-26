.PHONY = init, build, start, shutdown, restart, test

CC=javac

# Repertoire Hugo
#CATALINA=~/Documents/Cours/M1/S2/IBD/Project/Web

# Repertoire Yasin
CATALINA=~/M1/S2/SVNCOURS/IBD/Project/Web

init:
	export JAVA_HOME=/usr
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
