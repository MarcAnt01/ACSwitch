# Advanced Charging Switch

## Low Level Control

I have already put effort to the documentation explaining how switching charging state
works in Android and what are some obstacles to overcome in my project 'My Charging Controller'.
Here is another attempt of the same :)

#### Configuration

Configuring is the initial part of the work, it basically consists of detecting which switch is
to be used and what are the true/false values. ACSwitch, for this, also checks if they
work in addition to their existence.

#### Switching

Switching charging state basically requires just writing positive or negative value
to the switch for enabling or disabling respectively. Keep in mind that there are some bad
things discussed in following sections:

- Checking power connection

    We have to check if the device is accepting power or not before switching charging:
this is required to prevent deep CPU overcycles caused by kernel continuously
failing due to insufficient current. Here, we face lack of native APIs to detect
charger connection state, using `dumpsys battery` is not reliable across platforms
and we don't currently build java code. We parse `POWER_SUPPLY_ONLINE` in `uevents`
of input power supplies for the purpose, which still, is more or less unreliable.

- Inconsistent switching

    There are some kernels which don't stick changes to switches as made by us.
In this case we lack hardware capable of switching or kernel/drivers that
allow it. We struggle against unreliable and inconsistent charging state, switch
state and connection parameters. At worst, there is no possible way out but
to change kernel (if kernel/driver issue) for this problem.

- Irresponsive kernels

    Sometimes is the situation where kernel will not see the change to switch for
certain a period of some minutes, likely until battery is upleveled a little. In
such scenarios, we're lacking well-coded kernel (Those 'It just works!' you know)
and need to make the kernel take the change. OK, there is no direct way to do so
other than some software patching trickery, but I have found it useful in several
cases that to invert switch first and then to target state provoking kernel
by doing in this way.
