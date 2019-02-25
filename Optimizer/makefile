Optimizer.exe		: 	Main.o graphics.o transform.o WorldState.0 fuzzylogic.o
	g++ -O2 -std=c++11  -Wl,-s -o Optimizer.exe Main.o graphics.o transform.o WorldState.o fuzzylogic.o -l gdi32 -static-libgcc -static-libstdc++
			
Main.o		:	Main.cpp ../Assignment2_159302/fuzzylogic.h ../Assignment2_159302/WorldState.h 
	g++ -O2  -std=c++11  -c -fpermissive -fconserve-space  -Wno-write-strings Main.cpp
	
transform.o		:	 ../Assignment2_159302/transform.cpp ../Assignment2_159302/transform.h
	g++ -O2  -std=c++11  -c -fpermissive -fconserve-space  -Wno-write-strings ../Assignment2_159302/transform.cpp	

fuzzylogic.o	:	 ../Assignment2_159302/fuzzylogic.cpp ../Assignment2_159302/fuzzylogic.h
	g++ -O2  -std=c++11  -c -fpermissive -fconserve-space  -Wno-write-strings ../Assignment2_159302/fuzzylogic.cpp		
	
graphics.o		:	 ../Assignment2_159302/graphics.cpp ../Assignment2_159302/graphics.h
	g++ -O2  -std=c++11  -c -fpermissive -fconserve-space -Wno-write-strings  ../Assignment2_159302/graphics.cpp
	
WorldState.0		:	 ../Assignment2_159302/WorldState.cpp ../Assignment2_159302/WorldState.h
	g++ -O2  -std=c++11  -c -fpermissive -fconserve-space -Wno-write-strings  ../Assignment2_159302/WorldState.cpp

clean:
	del *.o
	del *.exe