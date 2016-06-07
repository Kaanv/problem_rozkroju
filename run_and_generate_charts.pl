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
my $output;

my $max_search = 1000;
my $max_neigh = 50;

my $current_data = "$max_search $max_neigh ";

my $name;

for (my $i = 0; $i < @file; $i++)
{
	if ($file[$i] =~ /('.*')\r?\n/)
	{
		if ($current_data ne "$max_search $max_neigh ")
		{
			$output = `./problem $current_data`;
			$current_data = "$max_search $max_neigh ";
			print $name, ": $output";
		}

		$name = $1;
		next;
	}
	while ($file[$i] =~ /([0-9\.]+)/g)
	{
		$current_data = $current_data . $1 . " ";
	}
}

$output = `./problem $current_data`;
print "$name", ": $output";

