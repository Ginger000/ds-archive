num_vert = 9;
adj = zeros(num_vert);
tol = 10e-5;
alpha = 0.85;

%Cheese,2,One,Two
%One,3,Five,Size,Cheese
%Two,2,One,
Five

    std = 1 / num_vert * ones(num_vert, 1);

outs = zeros(9, 9);
outs(4,1)=1;
outs(1,2)=1;
outs(2,3)=1;
outs(3,4)=1;
outs(3,5)=1;outs(7,5)=1;
outs(2,6)=1;outs(5,6)=1;
outs(6,7)=1;outs(8,7)=1;
outs(8,9)=1;

for
i = 1
:num_vert
if outs(:,i) ==
zeros(num_vert,
1)
outs(:,i) =
std;
else
outs(:,i) = outs(:,i)./

sum (outs(

:,i));
end
    end
outs = outs * alpha + (1 - alpha) * std * ones(1, num_vert);

error = norm(std);
pos = ones(num_vert, 1);
counter = 0;
while error >
tol
    buffer = outs * pos;
error = norm(buffer - pos);
pos = buffer;
pos'
counter = 1 + counter;
end
    outs
counter


