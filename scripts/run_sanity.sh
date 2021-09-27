#!/bin/bash

printf "\nRunning add1 test!\n"
../simulate binary/add1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/add1-py.dump

printf "Running add2 test!\n"
../simulate binary/add2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/add2-py.dump

printf "Running and1 test!\n"
../simulate binary/and1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/and1-py.dump

printf "Running and2 test!\n"
../simulate binary/and2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/and2-py.dump

printf "Running br test!\n"
../simulate binary/br-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/br-py.dump

printf "Running brp test!\n"
../simulate binary/brp-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brp-py.dump

printf "Running brz test!\n"
../simulate binary/brz-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brz-py.dump

printf "Running brzp test!\n"
../simulate binary/brzp-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brzp-py.dump

printf "Running brn test!\n"
../simulate binary/brn-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brn-py.dump

printf "Running brnp test!\n"
../simulate binary/brnp-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnp-py.dump

printf "Running brnz test!\n"
../simulate binary/brnz-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnz-py.dump

printf "Running brnzp test!\n"
../simulate binary/brnzp-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnzp-py.dump

printf "Running jmp test!\n"
../simulate binary/jmp-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jmp-py.dump

printf "Running jsr test!\n"
../simulate binary/jsr-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jsr-py.dump

printf "Running jsrr test!\n"
../simulate binary/jsrr-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jsrr-py.dump

printf "Running ldb1 test!\n"
../simulate binary/ldb1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/ldb1-py.dump

printf "Running ldb2 test!\n"
../simulate binary/ldb2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/ldb2-py.dump

printf "Running ldw1 test!\n"
../simulate binary/ldw1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/ldw1-py.dump

printf "Running ldw2 test!\n"
../simulate binary/ldw2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/ldw2-py.dump

printf "Running lea test!\n"
../simulate binary/lea-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/lea-py.dump

printf "Running lshf test!\n"
../simulate binary/lshf-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/lshf-py.dump

printf "Running not test!\n"
../simulate binary/not-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/not-py.dump

printf "Running ret test!\n"
../simulate binary/ret-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/ret-py.dump

printf "Running rshfa test!\n"
../simulate binary/rshfa-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/rshfa-py.dump

printf "Running rshfl test!\n"
../simulate binary/rshfl-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/rshfl-py.dump

printf "Running stb1 test!\n"
../simulate binary/stb1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/stb1-py.dump

printf "Running stb2 test!\n"
../simulate binary/stb2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/stb2-py.dump

printf "Running stw1 test!\n"
../simulate binary/stw1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/stw1-py.dump

printf "Running stw2 test!\n"
../simulate binary/stw2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/stw2-py.dump

printf "Running trap test!\n"
../simulate binary/trap-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/trap-py.dump

printf "Running xor1 test!\n"
../simulate binary/xor1-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/xor1-py.dump

printf "Running xor2 test!\n"
../simulate binary/xor2-py.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/xor2-py.dump