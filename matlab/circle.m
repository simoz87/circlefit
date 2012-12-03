function [ ret ] = circle (X,Y, r,noise1,noise2,n)
ret=zeros([n 2]);
alphas=rand([n,1])*2*pi;
fid=fopen('out.txt','w');
M=max(abs(X),abs(Y));
for i=1:n
  sX=X+r*cos(alphas(i));
  sY=Y+r*sin(alphas(i));
  ret(i,:)=[sX,sY] + noise1*randn([1 2])+ (rand()<noise2)*rand([1,2]);
  fprintf(fid,'%f\t%f\n',ret(i,1),ret(i,2));
end;
fclose(fid);
