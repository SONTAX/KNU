#!/usr/bin/ruby
# frozen_string_literal: true

# a = Array.new(14)
a = [-3, 12, 0, 0, 0, 12, 12, 12, -3, -3, -3, 12, 12, -3]

temp1 = Array.new(0)
temp2 = Array.new(0)
temp3 = Array.new(0)

i = 0
while i < 14
  if a[i].to_i.zero?
    temp1.push(a[i])
  elsif a[i].to_i.negative?
    temp2.push(a[i])
  elsif a[i].to_i.positive?
    temp3.push(a[i])
  end
  i += 1
end

puts 'a: '
i = 0
while i < 14
  printf("#{a[i]}\t")
  i += 1
end

c = temp1 + temp2 + temp3

puts '', 'c: '
i = 0
while i < 14
  printf("#{c[i]}\t")
  i += 1
end
