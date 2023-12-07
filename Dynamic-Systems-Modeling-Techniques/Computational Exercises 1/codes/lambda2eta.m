function eta = lambda2eta(lambda)
    tmp_eta = 0:0.001:1;
    x = log(tmp_eta)./(tmp_eta-1);
    tmp_lambda = x.*exp(-x);
    [void, pos] = min(abs(lambda-tmp_lambda));
    eta=tmp_eta(pos);
end