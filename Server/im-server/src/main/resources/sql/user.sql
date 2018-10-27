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

-- 测试数据
insert into user values('1234qwerasdf', '594542356', '594542356@qq.com', '风一样离去', 'xxxxxxxx', 0, 0, '2018-10-10 10:10:10', null);
