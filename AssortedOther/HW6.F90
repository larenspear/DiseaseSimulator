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

    subroutine PrimeList(list_of_primes,n)
    use PrimeNumbers
    
    implicit none
    integer, dimension(:), allocatable :: list_of_primes
    integer :: i,j,n
    
    allocate(list_of_primes(n))
        j = 1
        do i=1,n
            list_of_primes(i) = NextPrime(j)
            j = NextPrime(j)
        end do
 
    print*, list_of_primes
   
    return
    
    end subroutine PrimeList

    subroutine NextPrevious(r,p,q)
    use PrimeNumbers
    
    implicit none
    integer :: r,p,q

    p = PreviousPrime(r)
    q = NextPrime(r)

    print *,p 
    print*,"is the previous prime number"
    print*,q 
    print*,"is the next prime number"
    
    return
    
    end subroutine NextPrevious

    program FindPrimes
    use PrimeNumbers
    
    implicit none   
    integer :: n,r,p,q

    real, dimension(:), allocatable :: list_of_primes(:)

    print *, "Enter number of desired prime numbers"
    read *, n

    print *, "Enter number to find next and previous prime"
    read *,r
    
    allocate(list_of_primes(n))

    call PrimeList(list_of_primes, n)
    print*,""
    call NextPrevious(r, p, q) 

    end program FindPrimes
