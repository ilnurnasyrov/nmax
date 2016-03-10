require "bundler/gem_tasks"
require "rspec/core/rake_task"

require "rake/extensiontask"

Rake::ExtensionTask.new("bignums_elector")

RSpec::Core::RakeTask.new(:spec)

task spec: "compile:bignums_elector"
task default: :spec
