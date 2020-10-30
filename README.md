# Philosophers

Three different approaches to the [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). 
Philo_one implements it using a thread for every Philosophers and mutexes to protect the forks. The second implementations also uses threads for philosophers, but semaphores to protect the forks. 
The third implementation also uses semaphores, but this time each philosopher runs in it's own process.
