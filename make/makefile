# This is the make file for compilation and generation of exe from src prg files for the project
# here server_exe is the executable for the concurrent multithreaded server

SRC=../src
SSRC=../src/server
CSRC=../src/client
BIN=../bin
INC=../include
OBJ=../obj
LOG=../log

CC = gcc

OFLAGS = -o
CFLAGS = -c -g -Wall -Werror -Wunused
PFLAGS = -lpthread
GFLAGS = `pkg-config --cflags --libs glib-2.0` 
IFLAGS = -I$(INC)

GCOVFLAGS = -fprofile-arcs -ftest-coverage
SPLINTFLAG = splint -exportlocal -I$(INC) -skipposixheaders -skipisoheaders -D__builtin_va_list=int 
VFLAGS = valgrind -v --tool=memcheck --log-file=$(LOG)/val_server_log --leak-check=yes --show-reachable=yes 

all: clean common_crypto_obj server_exe client_exe

common_crypto_obj : $(SRC)/common_crypto.c 
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC)/common_crypto.c
	mv *.o $(OBJ)

server_exe : server_prg_obj $(OBJ)/client_handler.o $(OBJ)/new_user_processing.o $(OBJ)/existing_user_processing.o $(OBJ)/broadcast_handler.o $(OBJ)/client_authentication.o $(OBJ)/gslist_util.o $(OBJ)/is_user_exist.o $(OBJ)/add_to_reg_user_file.o $(OBJ)/active_session.o $(OBJ)/send_recv.o $(OBJ)/common_crypto.o $(OBJ)/log_server_report.o $(OBJ)/server_prg.o	
	$(CC) $(PFLAGS) $(GFLAGS) $(GCOVFLAGS) $(OBJ)/client_handler.o $(OBJ)/new_user_processing.o $(OBJ)/existing_user_processing.o $(OBJ)/broadcast_handler.o $(OBJ)/client_authentication.o $(OBJ)/gslist_util.o $(OBJ)/is_user_exist.o $(OBJ)/add_to_reg_user_file.o $(OBJ)/active_session.o $(OBJ)/send_recv.o $(OBJ)/common_crypto.o $(OBJ)/log_server_report.o $(OBJ)/server_prg.o $(OFLAGS) $(BIN)/server_exe

server_prg_obj : client_handler_obj new_user_processing_obj existing_user_processing_obj broadcast_handler_obj client_authentication_obj is_user_exist_obj add_to_reg_user_file_obj gslist_util_obj active_session_obj send_recv_obj log_server_report_obj $(SSRC)/server_prg.c $(INC)/server_util.h 
	$(CC) $(CFLAGS) $(PFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/server_prg.c
	mv *.o $(OBJ)

client_handler_obj : $(SSRC)/client_handler.c $(INC)/server_util.h 
	$(CC) $(CFLAGS) $(PFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/client_handler.c
	mv *.o $(OBJ)

new_user_processing_obj : $(SSRC)/new_user_processing.c $(INC)/server_util.h $(INC)/common_crypto.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/new_user_processing.c
	mv *.o $(OBJ)

existing_user_processing_obj : $(SSRC)/existing_user_processing.c $(INC)/server_util.h $(INC)/common_crypto.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/existing_user_processing.c
	mv *.o $(OBJ)

broadcast_handler_obj : $(SSRC)/broadcast_handler.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(PFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/broadcast_handler.c
	mv *.o $(OBJ)

client_authentication_obj : $(SSRC)/client_authentication.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/client_authentication.c
	mv *.o $(OBJ)

gslist_util_obj : $(SSRC)/gslist_util.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/gslist_util.c
	mv *.o $(OBJ)

active_session_obj : $(SSRC)/active_session.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/active_session.c
	mv *.o $(OBJ)

is_user_exist_obj : $(SSRC)/is_user_exist.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/is_user_exist.c
	mv *.o $(OBJ)
 
add_to_reg_user_file_obj : $(SSRC)/add_to_reg_user_file.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/add_to_reg_user_file.c
	mv *.o $(OBJ)

send_recv_obj : $(SSRC)/send_recv.c $(INC)/server_util.h	 
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/send_recv.c
	mv *.o $(OBJ)

log_server_report_obj : $(SSRC)/log_server_report.c $(INC)/server_util.h 
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(SSRC)/log_server_report.c
	mv *.o $(OBJ)

client_exe : client_prg_obj $(OBJ)/new_user.o $(OBJ)/get_login_details.o $(OBJ)/existing_user.o $(OBJ)/brdcst_recv_handler.o $(OBJ)/brdcst_send_handler.o $(OBJ)/client_send_recv.o $(OBJ)/log_client_report.o $(OBJ)/common_crypto.o $(OBJ)/client_prg.o
	$(CC) $(PFLAGS) $(GCOVFLAGS) $(OBJ)/new_user.o $(OBJ)/get_login_details.o $(OBJ)/existing_user.o $(OBJ)/brdcst_recv_handler.o $(OBJ)/brdcst_send_handler.o $(OBJ)/client_send_recv.o $(OBJ)/log_client_report.o $(OBJ)/common_crypto.o $(OBJ)/client_prg.o $(OFLAGS) $(BIN)/client_exe

client_prg_obj : new_user_obj get_login_details_obj existing_user_obj brdcst_recv_handler_obj brdcst_send_handler_obj client_send_recv_obj log_client_report_obj $(CSRC)/client_prg.c $(INC)/client_util.h
	$(CC) $(CFLAGS) $(PFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/client_prg.c
	mv *.o $(OBJ)

new_user_obj : $(CSRC)/new_user.c $(INC)/client_util.h $(INC)/common_crypto.h
	$(CC) $(CFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/new_user.c
	mv *.o $(OBJ)

get_login_details_obj : $(CSRC)/get_login_details.c $(INC)/client_util.h 
	$(CC) $(CFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/get_login_details.c
	mv *.o $(OBJ)

existing_user_obj : $(CSRC)/existing_user.c $(INC)/server_util.h $(INC)/common_crypto.h
	$(CC) $(CFLAGS) $(PFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/existing_user.c
	mv *.o $(OBJ)

brdcst_recv_handler_obj : $(CSRC)/brdcst_recv_handler.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(PFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/brdcst_recv_handler.c
	mv *.o $(OBJ)

brdcst_send_handler_obj : $(CSRC)/brdcst_send_handler.c $(INC)/server_util.h
	$(CC) $(CFLAGS) $(PFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/brdcst_send_handler.c
	mv *.o $(OBJ)

client_send_recv_obj : $(CSRC)/client_send_recv.c $(INC)/client_util.h 
	$(CC) $(CFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/client_send_recv.c
	mv *.o $(OBJ)

log_client_report_obj : $(CSRC)/log_client_report.c $(INC)/client_util.h 
	$(CC) $(CFLAGS) $(GFLAGS) $(IFLAGS) $(GCOVFLAGS) $(CSRC)/log_client_report.c
	mv *.o $(OBJ)

clean:
	rm -f $(BIN)/server_exe $(BIN)/client_exe $(OBJ)/*.o

valgrind:
	$(VSFLAGS) $(BIN)/server_exe 10.203.161.16 16550
