#!/usr/bin/ruby
# frozen_string_literal: true

# 2

p = 4
t = 8
r = 0
diapason = ((p**r) * (1 - (p**-t))).round
puts 'Diapason: ', diapason
