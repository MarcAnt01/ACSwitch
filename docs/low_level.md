# Advanced Charging Switch

## Low Level Control

I have already put efforts to document how switching charging state on Android
works and what are some obstacles to overcome in my project 'My Charging Controller'.
Here is another attempt of the same :)

#### Configuration

Configuring is initial part of the job, it's basically detecting which switch is
to be used and what are true/false values. ACSwitch, for this, does not actually
test if they work, rather only their existence is tested.

#### Switching

Switching charging state basically requires just writing positive or negative value
to the switch for enabling and disabling respectively. Though there are some bad
things discussed in following sections:

- Checking power connection

    We must check if device is accepting power or not before switching charging,
this is required to prevent deep CPU overcycles caused by kernel continuously
failing due to insufficient current. Here, we face lack of native APIs to detect
charger connection state, using `dumpsys battery` is not reliable across platforms
and we don't currently build java code. We parse `POWER_SUPPLY_ONLINE` in `uevents`
of input power supplies for the purpose, which still, is more or less unreliable.

- Inconsistent switching

    There are some kernels which don't stick changes to switches as made by us.
We, in this case lack either hardware capable of switching or kernel/drivers that
allow it. We struggle against unreliable and inconsistent charging state, switch
state and connection parameters. And the worst, there is no possible way out but
to change kernel (if kernel/driver issue) for this problem.

- Irresponsive kernels

    Sometimes is the situation where kernel will not see the change to switch for
certain a period of some minutes, likely until battery is upleveled a little. In
such scenarios, we're lacking well-coded kernel (Those 'It just works!' you know)
and need to make the kernel take the change. OK, there is no direct way to do so
other than some software patching trickery, but I have found it useful in several
cases that inverting switch first and then to target state helps provoking kernel
on doing so.
