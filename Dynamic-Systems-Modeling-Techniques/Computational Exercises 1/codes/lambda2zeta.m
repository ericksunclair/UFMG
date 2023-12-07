function zeta = lambda2zeta(lambda)
    tmp_zeta = 0:0.001:0.99;
    x = acos(tmp_zeta)./sqrt(1-tmp_zeta.^2);
    tmp_lambda = x.*exp(-tmp_zeta.*x);
    [void, pos] = min(abs(lambda-tmp_lambda));
    zeta = tmp_zeta(pos);
end