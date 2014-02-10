
BUILD = echo_client segfault segfault2 JSONParser

all: $(BUILD)

clean:
	$(RM) $(BUILD)
	$(RM) $(BUILD:%=Clean\ System\ Files/%.abc)
	$(RM) $(BUILD:%=Clean\ System\ Files/%.o)

CLM = clm
CLMFLAGS = \
	-fusion \
	-I . \
	-I /tmp/tmproot/clean/lib/StdLib \
	-I /tmp/tmproot/clean/lib/TCPIP  \
	-I /tmp/tmproot/clean/lib/Parsers \
	-I /tmp/tmproot/clean/lib/Parsers/LanguageDependent/English

.SUFFIXES: .icl

.icl:
	$(CLM) $(CLMFLAGS) $* -o $*
