#!/usr/bin/ruby
# frozen_string_literal: true

a = Array.new(14)
c = Array.new(14)

i = 0
while i < 14
  a[i] = rand(-10..10)
  c[i] = rand(-10..10)
  i += 1
end

b = a & c

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
puts '', 'b: '
i = 0
while i < 14
  printf("#{b[i]}\t")
  i += 1
end
