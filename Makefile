all: speedtest_int speedtest_long speedtest_float speedtest_lim

speedtest_int: speedtest.cc safeint.hh
	g++ -DTYPE=int -g -O2 -o speedtest_int speedtest.cc

speedtest_long: speedtest.cc safeint.hh
	g++ -DTYPE=SafeIntLong -g -O2 -o speedtest_long speedtest.cc

speedtest_float: speedtest.cc safeint.hh
	g++ -DTYPE=SafeIntFloat -g -O2 -o speedtest_float speedtest.cc

speedtest_lim: speedtest.cc safeint.hh
	g++ -DTYPE=SafeIntLim -g -O2 -o speedtest_lim speedtest.cc

clean:
	rm -f speedtest_long
	rm -f speedtest_float
	rm -f speedtest_lim
