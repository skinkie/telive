default: telive

telive: telive.c telive.h telive-zmq.c telive-zmq.h
	gcc telive.c telive-zmq.c -o telive -lncurses -lzmq -g

