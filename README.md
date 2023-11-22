# Philosophers

## Usage

``make`` to compile and create the **philo** executable
 
``./philo number_of_philosophers time_to_die time_to_eat time_to_sleep``

or

``./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]``

#### Examples

``./philo 5 800 200 200`` no one should die.

``./philo 5 800 200 200 7`` no one should die, and the simulation has to stop when every philosopher eat at least 7 times.

``./philo 4 410 200 200`` no one should die.

``./philo 4 310 200 100`` a philosopher should die.

``./philo 1 800 200 200`` the philosopher should not eat and should die.

## Tester

If you want to test your project use this repository : https://github.com/newlinuxbot/Philosphers-42Project-Tester.
