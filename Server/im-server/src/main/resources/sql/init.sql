-- zh2683 2018-10-28 用户表
drop table if exists user;
create table user(
  id varchar(32),
  code varchar(20) unique not null,
  email varchar(50) unique not null,
  nickname varchar(20) not null,
  password varchar(12) not null,
  sex int,
  `delete` int,
  createTime datetime not null,
  modifyTime datetime,
  primary key(id)
) engine=innodb;

