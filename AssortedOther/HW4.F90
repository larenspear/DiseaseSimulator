    program primenumbers
    
    implicit none
    
    integer :: i,j
    
    do i = 2, 100
        if (i == 2 .or. i == 3 .or. i == 5 .or. i == 7) then
            print*, int(i), "is prime" 
        else if (mod(i,2) == 0) then
            print *,int(i), "is not prime; it is divisible by 2"
        else if (mod(i,3) == 0) then
            print *, int(i),"is not prime; it is divisible by 3"
        else if (mod(i,5) == 0) then
            print *, int(i),"is not prime; it is divisible by 5"
        else if (mod(i,7) == 0) then
            print *, int(i),"is not prime; it is divisible by 7"
        else
            print*, int(i), "is prime"
        end if
    end do
    end program primenumbers
