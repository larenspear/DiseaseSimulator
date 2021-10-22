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
        do while (IsPrime(n2) .eqv. .false.)
            n2 = n2+1
        end do
        NextPrime = n2

        end function NextPrime

        integer function PreviousPrime(n) !returns previous prime

        integer :: n,n2
        n2 = n-1
        do while (IsPrime(n2) .eqv. .false.)
            n2 = n2-1
        end do
        PreviousPrime = n2

        end function PreviousPrime

    subroutine PrimeList(list_of_primes,n)

    implicit none
    integer, dimension(:), allocatable :: list_of_primes
    integer :: i,j,n

    allocate(list_of_primes(n))
        j = 1
        do i=1,n
            list_of_primes(i) = NextPrime(j)
            j = NextPrime(j)
        end do

    !print*, list_of_primes

    return

    end subroutine PrimeList

    end module PrimeNumbers

    program Goldbach !r, p, and q all prime while p-r == q-p

    use PrimeNumbers

    implicit none
    integer :: i, p, q, r, distance
    integer, dimension(:), allocatable :: list_of_primes
    integer, dimension(:), allocatable :: distance_list    

    call PrimeList(list_of_primes,10000)
    allocate(distance_list(10000))

    do i=5,10000
        p = list_of_primes(i)
        q = list_of_primes(i+1)
        r = list_of_primes(i-1)
        do while (p-r /= q-p)
            if (p-r > q-p) then
                q = NextPrime(q)
            else if (p-r < q-p) then
                r = PreviousPrime(r)
            end if
        end do
        distance = q - p
        distance_list(i) = distance      
    end do

    print*, distance_list

    print*, "average distance" 

    print*, sum(distance_list) / size(distance_list)

    print*, "max distance"

    print*, maxval(distance_list)

    print*, "minimum distance"

    print*, minval(distance_list)

    end program Goldbach
    
