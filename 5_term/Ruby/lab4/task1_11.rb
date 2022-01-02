#!/usr/bin/ruby
# frozen_string_literal: true

a = Array.new(14)

i = 0
while i < 14
  a[i] = rand(-10..10)
  i += 1
end

temp1 = a[0..6]
temp2 = a[7..13]
temp1 = temp1.reverse
temp2 = temp2.reverse

c = temp1 + temp2

puts 'a: '
i = 0
while i < 14
  printf("#{a[i]}\t")
  i += 1
end

puts '', 'c: '
i = 0
while i < 14
  printf("#{c[i]}\t")
  i += 1
end
