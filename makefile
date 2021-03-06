OBJ = base64.o crypt.o sha512.o

first: passgen.bin passread.bin
	
user-install: first
	mkdir ~/bin 2>/dev/null || true
	cp passgen.bin ${HOME}/bin/passgen
	cp passread.bin ${HOME}/bin/passread
	if grep --quiet "#PassManager" ${HOME}/.bashrc; then true; else cat profile >> ${HOME}/.bashrc; fi

install: first
	cp passgen.bin /usr/bin/passgen
	cp passread.bin /usr/bin/passread
	if grep --quiet "#PassManager" /etc/bash/bashrc; then true; else cat profile >> /etc/bash/bashrc; fi

passgen.bin: passgen.o $(OBJ)
	g++ -o $@ $< $(OBJ)

passread.bin: passread.o $(OBJ)
	g++ -o $@ $< $(OBJ)

%.o: %.cpp base64.h crypt.h %.h
	g++ -c -o $@ $<

clean:
	rm *.o *.bin || true
