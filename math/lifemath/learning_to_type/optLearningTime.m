%%
% Returns the optimum number of days to be spent on learning how to type,
% and the words per minute you will acheived. You should spent this amount
% of time on learning, before starting the task of typing your pages.
%%
function [days_learning, wpm_target] = optLearningTime( xdata_v, ydata_v, words_to_type, typing_time_per_day)

% t => time in days, w => words per minute
    syms t w;
    %% Using Logistic function as the saturation function, with parameter p
    % Other options include tanh
    % t is the time spent on learning, F(t) = words per minute achieved.
    F = @(p,t) p(3)./(1 + exp(p(1) - p(2)*t));
    %% Pick an arbitrary starting point for parameters p(1), p(2), ...
	p = [0, 0, 0];
    
    %% Fit the curve and find p
    options  = optimset('Display', 'off'); % Supress display from lsqcurvefit
	[p,~,~,exitflag,~] = lsqcurvefit(F, p, xdata_v, ydata_v, [], [], options);
    assert(exitflag == 1 || exitflag == 3, 'Could not find a solution');

    %ezplot(F(p, x), [0, 200]);

    %% Optimize total-time t = to + t1, where t0 = time to learn, and t1
    %% is the time to type the words

    % Model t0 first, as inverse function of F(t), and replace sym 't' with 'w'
    g = subs(finverse(F(p, t)), t, w);

    %ezplot(g, [0, 200]);
    % Find w that optimizes Total time (expressed as a function of w)
	total_time = g + (words_to_type/w)/typing_time_per_day;
	wpm_target = solve(diff(total_time));       % Calculus 101
    % To avoid returning negative days learning, set the minimum wpm_target
    % to be the wpm you can acheive with no additional learning (t = 1)
    min_wpm_target = subs(F(p,t), t, 1);
    wpm_target = max(wpm_target, min_wpm_target);
	days_learning = subs(g, w, wpm_target);
end

