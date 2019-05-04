#
#   Newtonic - Graphics for Physics
#   Copyright (C) 2019 Luca "ekardnam" Bertozzi <luca.bertozzi11@studio.unibo.it>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

CC=g++
CFLAGS=-Wall -Wextra --std=c++17 -ggdb
LDFLAGS=-lGL -lGLEW -lglfw

src := $(wildcard *.cpp)
obj := $(src:%.cpp=%.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^

.PHONY: test
test: $(obj)
	$(CC) $(LDFLAGS) -o newtonic-test $(obj)

.PHONY: clean
clean:
	rm $(obj)
	rm newtonic-test
