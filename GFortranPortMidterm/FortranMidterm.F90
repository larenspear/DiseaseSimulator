module PrimeNumbers
    implicit none

contains
    logical function IsPrime(n) !n int, returns True/False

        integer, intent(in) :: n
        integer :: i

        if(n <= 1) then
            IsPrime = .false.
            return
        end if

        if (n == 2 .or. n == 3) then
            IsPrime = .true.
            return
        end if

        if(mod(n,2) == 0 .or. mod(n,3) == 0) then
            IsPrime = .false.
            return
        end if

        i = 5
        do while(i*i <= n)
            if (mod(n,i) == 0 .or. mod(n,i+2) == 0) then
                IsPrime = .false.
                return
            end if
            i = i + 6
        end do
        IsPrime = .true.
        
    end function IsPrime

    integer function NextPrime(n) !returns prime number after n

        integer, intent(in) :: n
        integer :: candidate
        candidate = n + 1
        do while (.not. IsPrime(candidate))
            candidate = candidate + 1
        end do
        NextPrime = candidate

    end function NextPrime

    integer function PreviousPrime(n) !returns previous prime

        integer, intent(in) :: n
        integer :: candidate
        candidate = n - 1
        do while (.not. IsPrime(candidate))
            candidate = candidate - 1
        end do
        PreviousPrime = candidate

    end function PreviousPrime

    subroutine PrimeList(list_of_primes,n)

        implicit none
        integer, dimension(:), allocatable, intent(out) :: list_of_primes
        integer, intent(in) :: n
        integer :: i
        integer :: j

        allocate(list_of_primes(n))
        j = 1
        do i=1,n
            list_of_primes(i) = NextPrime(j)
            j = NextPrime(j)
        end do

    end subroutine PrimeList

end module PrimeNumbers

program Goldbach !r, p, and q all prime while p-r == q-p

    use PrimeNumbers
    implicit none
    
    integer :: i, p, q, r
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
        distance_list(i) = q - p  
    end do

    print *, distance_list

    print *, "Average Distance:", sum(distance_list) / size(distance_list)

    print *, "Maximum Distance:", maxval(distance_list)

    print *, "Minimum Distance:", minval(distance_list)

    deallocate(distance_list)
    deallocate(list_of_primes)

end program Goldbach
    
