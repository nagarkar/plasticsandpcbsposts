% Identify the learning curve. The X axis represents the number of days
% spent learning, and the Y axis represents the words per minute acheived.
% At day '0', Y represents the WPM speed to begin with.
xdata_v = [0  15  30  200];
ydata_v = [10 25 40  60];

%typing_time_per_day  == ttpd, in minutes.
ttpd= 60;

%%%%%
% Solve and print answer for some sample "pages"
%%%%%
pages = 100;
res = zeros(2,1);
[res(1), res(2)] = optLearningTime(xdata_v, ydata_v, pages*30*8, ttpd);
res = round(res);
sprintf('Learning time for %i pages is %i, and wpm is %i', pages, res(1), res(2))

%%%%%
% Graph
%%%%%
% Identify the range of pages we are going to do a graph for.
range = 1:50:10000;
learning_time_v = zeros(length(range));
wpm_v = zeros(length(range));
idx = 1;
res = zeros(2,1);
for pages = range
    words = pages*30*8;	% # pages * 30 lines/page * 8 words/line.
    [learning_time_v(idx), wpm_v(idx)] = optLearningTime(xdata_v, ydata_v, words, ttpd);
    %learning_time_v(idx) = res(1);
    %wpm_v(idx) = res(2);
    idx = idx + 1;
end
plot(range, learning_time_v, range, wpm_v);
xlabel('Number of Pages to Type');
lgd = legend('Time to be spent on Learning', 'Words per minute achieved after learning');
lgd.Location = 'south';