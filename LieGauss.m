function LieGauss=LieGauss(A,n)
%B=ones(n);

for k=1:n-1
    m=k,a=abs(A(k,k));
    for  i=k+1:n
        if a<abs(A(i,k))
            m=i,a=abs(A(i,k));
        end
    end
    if m~=k
        for j=1:n
         %B(k,j)=A(k,j);
         t=A(k,j);
        A(k,j)=A(m,j);
        %A(m,j)=B(k,j);
        A(m,j)=t;
    end
    end
    for l=k+1:n
        A(l,k)=A(l,k)/A(k,k);
        for s=k+1:n
        A(l,s)=A(l,s)-A(l,k)*A(k,s);
    end
end
end
A