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
    
        recursive integer function NextPrime(n) !returns prime number after n
   
        integer :: n
 
        if (IsPrime(n) == .true.) then
            NextPrime = n
        else
            NextPrime = NextPrime(n+1)
        end if

        end function NextPrime

        recursive integer function PreviousPrime(n) !returns previous prime

        integer :: n

        if (IsPrime(n) == .true.) then
            PreviousPrime = n
        else
            PreviousPrime = PreviousPrime(n-1)
        end if 

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
