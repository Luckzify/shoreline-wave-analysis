function [fitresult, gof] = createFit1(js, ls)
%CREATEFIT1(JS,LS)
%  Create a fit.
%
%  Data for 'CurveFit' fit:
%      X Input : js
%      Y Output: ls
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  See also FIT, CFIT, SFIT.

%  Auto-generated by MATLAB on 07-Aug-2022 19:53:38


%% Fit: 'CurveFit'.
[xData, yData] = prepareCurveData( js, ls );

% Set up fittype and options.
ft = fittype( {'(sin(x-pi))', '((x-10)^2)', '1'}, 'independent', 'x', 'dependent', 'y', 'coefficients', {'a', 'b', 'c'} );

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft );

% Plot fit with data.
figure( 'Name', 'CurveFit' );
h = plot( fitresult, xData, yData );
legend( h, 'ls vs. js', 'CurveFit', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
xlabel( 'js', 'Interpreter', 'none' );
ylabel( 'ls', 'Interpreter', 'none' );
grid on

