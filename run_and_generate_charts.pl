#!/usr/bin/perl
use strict;
use warnings;

sub open_file
{
	my $file = $_[0];

	open (FH, "< $file") or die "Can't open $file for read: $!";
	my @lines = <FH>;
	close FH or die "Cannot close $file: $!"; 

	return @lines;
}

my @file = open_file($ARGV[0]);

sub create_data
{
	my $max_search = $_[0];
	my $max_neigh = $_[1];

	my $current_data = "$max_search $max_neigh ";

	my @data = ();

	for (my $i = 0; $i < @file; $i++)
	{
		if ($file[$i] =~ /('.*')\r?\n/)
		{
			if ($current_data ne "$max_search $max_neigh ")
			{
				push(@data, $current_data);
				$current_data = "$max_search $max_neigh ";
			}

			next;
		}
		while ($file[$i] =~ /([0-9\.]+)/g)
		{
			$current_data = $current_data . $1 . " ";
		}
	}
	push(@data, $current_data);
	return @data;
}

sub count_sum_for_data
{
	my @data = @{$_[0]};
	my $sum = 0;
	my $output;

	for (my $i = 0; $i < @data; $i++)
	{
		$output = `./problem ${data[$i]}`;
		$sum += $output;
	}

	return $sum;
}

for (my $max_search = 0; $max_search < 2000; $max_search += 100)
{
	for (my $max_neigh = 10; $max_neigh < 100; $max_neigh += 10)
	{
		my @data = create_data($max_search, $max_neigh);
		my $average = 0;
		for (my $i = 0; $i < 5; $i++)
		{
			$average += count_sum_for_data(\@data);
		}
		$average = $average/5;
		print "$max_search $max_neigh $average\n";
	}
}

