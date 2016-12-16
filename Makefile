include ../../Makefile.common
include ../../Makefile.model

INCLUDE += -I ../include

CXXFLAG += -fPIC
CXXFLAG += $(PARAMETER_DEFINES)

libmodelroutine.a: model_routine_config.o model_routine_grid.o model_routine_agent.o model_routine_mech_intrct.o model_routine_output.o
	$(AR) rcs libmodelroutine.a model_routine_config.o model_routine_grid.o model_routine_agent.o model_routine_mech_intrct.o model_routine_output.o

model_routine_config.o: model_routine_config.cpp model_define.h
	$(CXX) $(CXXFLAG) $(INCLUDE) -c model_routine_config.cpp -o model_routine_config.o

model_routine_grid.o: model_routine_grid.cpp model_define.h
	$(CXX) $(CXXFLAG) $(INCLUDE) -c model_routine_grid.cpp -o model_routine_grid.o

model_routine_agent.o: model_routine_agent.cpp model_define.h
	$(CXX) $(CXXFLAG) $(INCLUDE) -c model_routine_agent.cpp -o model_routine_agent.o

model_routine_mech_intrct.o: model_routine_mech_intrct.cpp model_define.h
	$(CXX) $(CXXFLAG) $(INCLUDE) -c model_routine_mech_intrct.cpp -o model_routine_mech_intrct.o

model_routine_output.o: model_routine_output.cpp model_define.h
	$(CXX) $(CXXFLAG) $(INCLUDE) -c model_routine_output.cpp -o model_routine_output.o

all:
	make

clean:
	$(RM) *.ilo
	$(RM) *.o
	$(RM) *.a
	$(RM) *~

clean_all:
	$(RM) *.ilo
	$(RM) *.o
	$(RM) *.a
	$(RM) *~
