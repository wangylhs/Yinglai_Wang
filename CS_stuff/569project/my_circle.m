
function out = my_circle(centre, rad, varargin)

	opt.n = 50;
    
    [opt,arglist] = tb_optparse(opt, varargin);

    % compute points on circumference
	th = [0:opt.n-1]'/ opt.n*2*pi;
    z = rad*cos(th) + centre(3);
    y = rad*sin(th) + centre(2);

    % add extra row if x-coordinate is specified, but circle is always in yz plane
    if length(centre) > 2
        x = ones(size(y))*centre(1);
        p = [x y z]';
    else
        p = [y z]';
    end

    if nargout > 0
        % return now
        out = p;
        return;
    else
        % else plot the circle
        p = [p p(:,1)]; % make it close
        if numrows(p) > 2
            plot3(p(1,:), p(2,:), p(3,:), arglist{:});
        else
            plot(p(1,:), p(2,:), arglist{:});
        end
    end
