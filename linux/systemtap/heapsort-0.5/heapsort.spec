%{!?sdt:%global sdt 1}
Name:		heapsort
Version:	0.5
Release:	1%{?dist}
Summary:	demo application of user space markers

Group:		Development/System
License:	GPLv2+
URL:		http://sourceware.org/systemtap/
Source0:	%{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%if %sdt
BuildRequires: systemtap-sdt-devel
%global tapsetdir	/usr/share/systemtap/tapset
%endif

%description

The heapsort example is a simple demonstration of the creation
systemtap markers in a user-space application. The heapsort example shows:

-Creating a RPM spec file for app with markers
-How to generate the marker code
-How to insert the markers into the application code
-A tapset using the markers
-Simple example stap scripts

%prep
%setup -q


%build
%configure \
%if %sdt
	--enable-systemtap \
	--with-tapset-install-dir=%tapsetdir
%endif
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%{_bindir}/heapsort
%if %sdt
%{tapsetdir}/*.stp
%endif

%changelog
* Fri Jan 8 2010 Will Cohen <wcohen@redhat.com> 0.5-1
- Use %global in spec file.

* Mon Nov 23 2009 Will Cohen <wcohen@redhat.com> 0.2-1
- Update README.

* Fri Nov 20 2009 Will Cohen <wcohen@redhat.com> 0.1-1
- Initial creation of RPM.
