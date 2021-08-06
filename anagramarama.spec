Name:           anagramarama
Version:        0.5
Release:        1%{?dist}
Summary:        Anagram puzzle game
License:        GPLv2+
URL:            http://identicalsoftware.com/anagramarama/

Source0:        %{url}/%{name}-%{version}.tgz

BuildRequires: cmake
BuildRequires: desktop-file-utils
BuildRequires: gcc-c++
BuildRequires: libgamerzilla-devel
BuildRequires: libappstream-glib
BuildRequires: make
BuildRequires: SDL-devel
BuildRequires: SDL_mixer-devel
Requires:      hicolor-icon-theme


%description
Anagramarama is a simple wordgame in which one tries to guess all the different
permutations of a scrambled word which form another word within the
time limit.  Guess the original word and you move on to the next
level.


%prep
%setup -q


%build
%cmake
%cmake_build


%install
%cmake_install
desktop-file-validate %{buildroot}%{_datadir}/applications/anagramarama.desktop
appstream-util validate-relax --nonet %{buildroot}%{_metainfodir}/anagramarama.metainfo.xml


%files
%doc readme
%license gpl.txt
%{_bindir}/anagramarama
%{_datadir}/anagramarama
%{_datadir}/icons/hicolor/*/apps/anagramarama.png
%{_metainfodir}/%{name}.metainfo.xml
%{_datadir}/applications/anagramarama.desktop
%{_datadir}/man/man6/anagramarama.6.gz


%changelog
* Fri Aug 06 2021 Dennis Payne <dulsi@identicalsoftware.com> - 0.5
- Initial build
