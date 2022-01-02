uses graphABC; 
const W = 800; H = 500;
var
  x0, y0, xLeft, yLeft, x, xRight, yRight, y, n: integer;
  a, b, c, d, x1, y1, t1, mx, my, dx, dy, num: real;
  i: byte;
  s: string;
begin
  {1.Малюємо координатну площину}
  SetWindowSize(W, H); 
  xLeft := 50;
  yLeft := 50;
  xRight := W - 50;
  yRight := H - 50;
  a := -6; b := 6; dx := 0.5;
  c := -6; d :=6; dy := 0.5;
  mx := (xRight - xLeft) / (b - a);                             
  my := (yRight - yLeft) / (d - c);                       
  x0 := trunc(abs(a) * mx) + xLeft;                                              
  y0 := yRight - trunc(abs(c) * my);                                           
  line(xLeft, y0, xRight + 10, y0); 
  line(x0, yLeft - 10, x0, yRight); 
  SetFontSize(12); 
  SetFontColor(clBlue); 
  TextOut(xRight + 20, y0 - 15, 'X'); 
  TextOut(x0 - 6, yLeft - 30, 'Y'); 
  SetFontSize(10); 
  SetFontColor(clBlue); 
  {2.Штрихуємо абсцису }
  n := round((b - a) / dx) + 1; 
  for i := 1 to n do
  begin
   num := a + (i - 1) * dx; 
   x := xLeft + trunc(mx * (num - a)); 
   Line(x, y0 - 3, x, y0 + 3); 
   str(Num:0:1, s);
   if abs(num) > 1E-15 then 
      TextOut(x - TextWidth(s) div 2, y0 + 7, s);
      SetFontSize(8);
  end;
  {3.Штрихуємо ординату }
  n := round((d - c) / dy) + 1; 
  for i := 1 to n do
  begin
    num := c + (i - 1) * dy; 
    y := yRight - trunc(my * (num - c));
    Line(x0 - 3, y, x0 + 3, y);
    str(num:0:1, s);
    if abs(num) > 1E-15 then 
      TextOut(x0 + 7, y - TextHeight(s) div 2, s);
      SetFontSize(8);
      end;
  TextOut(x0 - 10, y0 + 10, '0');
 {4.Графік будуємо по крапкам}
  x1 := 25;
  y1 := 25;
  t1 := 120;
  t1 := 0;
  while t1<=130 do
  begin
    x := x0 + round(x1 + 100 * Sin(0.99 * t1) - 100 * Cos(3.01 * t1)); 
    y := y0 - round(y1 - 100 * Cos(1.01 * t1) + 100 * Sin(15.03 * t1)); 
   putpixel(x,y,clgreen);
   t1:=t1+0.001*pi;
  end;
end.