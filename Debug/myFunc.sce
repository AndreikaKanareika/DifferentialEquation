clc;
function ydot=f(x,y)
    ydot=(2*(cos(x))^2*cotg(x)+y)./cotg(x);
endfunction

y0=0;
x0=-0.5;
x=x0:0.1:1.5;
y=ode(y0,x0,x,f);
plot(x,y);

x0=1.7;
y0=-16;
x=1.7:0.1:3
y=ode(y0,x0,x,f);
plot(x,y);

plot([1.6,1.6],[-20,40],'r--');
xgrid();
