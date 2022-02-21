num_vert = 5;
adj = zeros(num_vert);
tol = 10e-5;
alpha = 0.85;

%Cheese,2,One,Two
%One,3,Five,Size,Cheese
%Two,2,One,
Five

    label = containers.Map({'Cheese', 'One', 'Two', 'Five', 'Size'}, {1, 2, 3, 4, 5});
link = containers.Map({1, 2, 3, 4, 5}, {'Cheese', 'One', 'Two', 'Five', 'Size'});

std = 1 / num_vert * ones(num_vert, 1);

outs = [[0, 1, 1, 0, 0]',[1,0,0,1,1]',
[0,1,0,1,0]',zeros(1,5)',zeros(1,5)'];
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
outs
    outs = outs * alpha + (1 - alpha) * std * ones(1, num_vert);
outs;

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
    pos;
counter


