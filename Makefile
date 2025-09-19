Compilation_Flags_W = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

onegin.exe : onegin.o sort_functions.o get_functions.o 
		g++ $^ ${Compilation_Flags_W} -o onegin.exe

run: onegin.exe
	.\onegin.exe

%.o: %.c
	g++ ${Compilation_Flags_W} -c $< -o $@

clean:
	rm onegin.exe *.o

onegin.o: sort_functions.h get_functions.h