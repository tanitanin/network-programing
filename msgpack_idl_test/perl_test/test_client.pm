
package test_client;
use strict;
use warnings;
use AnyEvent::MPRPC::Client;

sub new {
  my ($self, $host, $port) = @_;
  my $client = AnyEvent::MPRPC::Client->new(
    host => $host,
    port => $port
    );
  bless { client => $client }, $self;
};

sub bar {
  my ($self, $lang, $xs) = @_;
  $self->{'client'}->call(bar => [$xs, $lang])->recv;
};

1;

