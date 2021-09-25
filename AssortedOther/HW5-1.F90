    module PrimeNumbers
    implicit none
    
    contains
        logical function IsPrime(n) !n int, returns True/False

        integer :: n, i
    
        if (n == 2 .or. n == 3 .or. n == 5 .or. n == 7) then
            IsPrime = .true.
        end if

        do i = 2, (n-1)
            if (mod(n,i) == 0) then
                IsPrime = .false.
                exit
            else
                IsPrime = .true.
            end if
        end do 
        end function IsPrime
    
        integer function NextPrime(n) !returns prime number after n
   
        integer :: n,n2
        n2 = n+1 
        do while (IsPrime(n2) == .false.)
            n2 = n2+1
        end do
        NextPrime = n2
        
        end function NextPrime

        integer function PreviousPrime(n) !returns previous prime

        integer :: n,n2
        n2 = n-1
        do while (IsPrime(n2) == .false.)
            n2 = n2-1
        end do
        PreviousPrime = n2

        end function PreviousPrime

    end module PrimeNumbers

    program FindPrimes

    use PrimeNumbers

    implicit none
    
    integer :: n

    print *, "Enter a number"

    read *, n

    print *, IsPrime(n)
    
    print *, NextPrime(n)

    print *, PreviousPrime(n)
    
    end program FindPrimes
